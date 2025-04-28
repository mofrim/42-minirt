/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:25:49 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/28 14:55:18 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



// Helper function to solve quadratic equation At^2 + Bt + C = 0
static t_quad_sol solve_quadratic(double a, double b, double c)
{
    t_quad_sol sol;

    sol.disc = b * b - 4 * a * c;
    if (sol.disc < 0)
    {
        sol.t1 = INF;
        sol.t2 = INF;
    }
    else
    {
        sol.t1 = (-b + sqrt(sol.disc)) / (2 * a);
        sol.t2 = (-b - sqrt(sol.disc)) / (2 * a);
    }
    return (sol);
}

// Check if intersection point q is within the cylinder height bounds
static bool is_within_bounds(t_cylinder *cyl, t_v3 q)
{
    t_v3 q_minus_p1 = v3_minus_vec(q, cyl->p1);
    double proj = v3_dot(q_minus_p1, cyl->axis);
    // Check if projection onto axis is between 0 and height
    return (proj >= 0 && proj <= cyl->height);
    // Note: Using >= 0 and <= height includes hits exactly on the cap edges
    // Use > 0 and < height if caps are handled entirely separately.
    // The logic below assumes caps are handled separately, so use > and <.
    // return (proj > EPSILON && proj < cyl->height - EPSILON); // Using epsilon
}


// Intersect with the two cap planes and check if inside radius
static double intersect_caps(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp, t_cylinder *cyl)
{
    double t_cap1 = INF, t_cap2 = INF;
    double denom;
    t_v3 hit_p;

    denom = v3_dot(ray_dir, cyl->axis);

    // Check intersection with plane at p1 (normal is -axis)
    // Plane equation: dot(P - p1, -axis) = 0 => dot(P, -axis) - dot(p1, -axis) = 0
    // Substitute P = origin + t * ray_dir:
    // dot(origin + t*ray_dir, -axis) = dot(p1, -axis)
    // dot(origin, -axis) + t*dot(ray_dir, -axis) = dot(p1, -axis)
    // t*(-denom) = dot(p1, -axis) - dot(origin, -axis)
    // t*(-denom) = dot(p1 - origin, -axis)
    // t = dot(p1 - origin, axis) / denom
    if (fabs(denom) > EPSILON) // Check if ray is not parallel to caps
    {
        t_cap1 = v3_dot(v3_minus_vec(cyl->p1, origin), cyl->axis) / denom;
        if (rp.tmin < t_cap1 && t_cap1 < rp.tmax) {
            hit_p = v3_add_vec(origin, v3_mult(ray_dir, t_cap1));
            // Check if hit point is within radius of the cap
            if (v3_norm_sq(v3_minus_vec(hit_p, cyl->p1)) > cyl->r_squared) // Use v3_norm_sq if available, else v3_norm*v3_norm
                t_cap1 = INF;
        } else {
             t_cap1 = INF;
        }

        // Check intersection with plane at p2 (normal is axis)
        // Plane eq: dot(P - p2, axis) = 0 => dot(P, axis) = dot(p2, axis)
        // dot(origin + t*ray_dir, axis) = dot(p2, axis)
        // t*denom = dot(p2, axis) - dot(origin, axis) = dot(p2 - origin, axis)
        // t = dot(p2 - origin, axis) / denom
        t_cap2 = v3_dot(v3_minus_vec(cyl->p2, origin), cyl->axis) / denom;
         if (rp.tmin < t_cap2 && t_cap2 < rp.tmax) {
            hit_p = v3_add_vec(origin, v3_mult(ray_dir, t_cap2));
            // Check if hit point is within radius of the cap
            if (v3_norm_sq(v3_minus_vec(hit_p, cyl->p2)) > cyl->r_squared)
                t_cap2 = INF;
         } else {
             t_cap2 = INF;
         }
    }

    return fmin(t_cap1, t_cap2); // Return the closer valid cap intersection
}


// Main cylinder intersection function
double cylinder_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp, t_cylinder *cyl)
{
    t_v3 delta_p;
    t_v3 v_perp, dp_perp;
    double a, b, c;
    t_quad_sol body_sol;
    double t_body = INF, t_caps = INF;
    t_v3 hit_p1, hit_p2;

    // Use p1 as the reference point pa from the PDF formula
    delta_p = v3_minus_vec(origin, cyl->p1);

    // Calculate terms needed for quadratic coefficients (see PDF [cite: 5])
    // v_perp = ray_dir - dot(ray_dir, cyl->axis) * cyl->axis;
    v_perp = v3_minus_vec(ray_dir, v3_mult(cyl->axis, v3_dot(ray_dir, cyl->axis)));
    // dp_perp = delta_p - dot(delta_p, cyl->axis) * cyl->axis;
    dp_perp = v3_minus_vec(delta_p, v3_mult(cyl->axis, v3_dot(delta_p, cyl->axis)));

    // Coefficients
    a = v3_dot(v_perp, v_perp); // a = v3_norm_sq(v_perp) if available
    b = 2 * v3_dot(v_perp, dp_perp);
    c = v3_dot(dp_perp, dp_perp) - cyl->r_squared; // c = v3_norm_sq(dp_perp) - cyl->r_squared

    if (fabs(a) < EPSILON) // Ray is parallel to cylinder axis
    {
         // Check if ray origin is inside the infinite cylinder
         if (c > 0) return INF; // Outside cylinder, parallel ray misses
         // Ray is parallel and potentially inside or on the cylinder surface.
         // Only cap intersections are possible in this case.
         return intersect_caps(origin, ray_dir, rp, cyl);
    }

    body_sol = solve_quadratic(a, b, c);

    if (body_sol.disc < 0) // No intersection with infinite cylinder body
    {
        // Still check caps
        return intersect_caps(origin, ray_dir, rp, cyl);
    }

    // Check if intersection points are within tmin/tmax and cylinder height bounds
    if (rp.tmin < body_sol.t1 && body_sol.t1 < rp.tmax)
    {
        hit_p1 = v3_add_vec(origin, v3_mult(ray_dir, body_sol.t1));
        if (is_within_bounds(cyl, hit_p1))
            t_body = body_sol.t1;
    }
    if (rp.tmin < body_sol.t2 && body_sol.t2 < rp.tmax)
    {
         hit_p2 = v3_add_vec(origin, v3_mult(ray_dir, body_sol.t2));
         if (is_within_bounds(cyl, hit_p2))
         {
             // If t1 was also valid, take the smaller one. If t1 was invalid, take t2.
             if (t_body == INF || body_sol.t2 < t_body)
                 t_body = body_sol.t2;
         }
    }

    // Intersect with caps
    t_caps = intersect_caps(origin, ray_dir, rp, cyl);

    // Return the smallest valid t from body or caps
    return fmin(t_body, t_caps);
}

t_colr cylinder_get_colr(t_scene scene, t_objlst cylobj, t_v3 hitpoint)
{
    t_cylinder *cyl;
    t_v3 normal_vec;
    t_v3 p_axis; // Point on axis corresponding to hitpoint height
    double m; // Projection length along axis from p1
    double dist_to_p1_plane;
    double dist_to_p2_plane;

    cyl = (t_cylinder *)cylobj.obj;

    // Calculate distance from hitpoint projection on axis to p1
    m = v3_dot(v3_minus_vec(hitpoint, cyl->p1), cyl->axis);

    // Check if hit is very close to either cap plane using epsilon
    dist_to_p1_plane = m;
    dist_to_p2_plane = cyl->height - m; // Distance from p2 plane along negative axis

    if (dist_to_p1_plane < EPSILON) { // Hit near cap 1 (at p1)
        normal_vec = v3_mult(cyl->axis, -1.0); // Normal points away from p2
    } else if (dist_to_p2_plane < EPSILON) { // Hit near cap 2 (at p2)
        normal_vec = cyl->axis; // Normal points away from p1
    } else { // Hit on cylinder body
        p_axis = v3_add_vec(cyl->p1, v3_mult(cyl->axis, m));
        normal_vec = v3_get_norm(v3_minus_vec(hitpoint, p_axis));
    }

    // Optional: Check if camera is inside and flip normal (like in sphere_get_colr)
    // This requires calculating if the camera position projected onto the axis
    // is between p1 and p2, and if its perpendicular distance to the axis
    // is less than the radius.
    // Simplified check (might not be fully robust for cylinders):
    // if (v3_dot(v3_minus_vec(scene.cam->pos, cyl->center), normal_vec) < 0) {
    //     normal_vec = v3_mult(normal_vec, -1.0);
    // }
    // A more accurate inside check:
    // t_v3 cam_on_axis = v3_add_vec(cyl->p1, v3_mult(cyl->axis, v3_dot(v3_minus_vec(scene.cam->pos, cyl->p1), cyl->axis)));
    // double cam_proj = v3_dot(v3_minus_vec(scene.cam->pos, cyl->p1), cyl->axis);
    // if (cam_proj > 0 && cam_proj < cyl->height && v3_norm_sq(v3_minus_vec(scene.cam->pos, cam_on_axis)) < cyl->r_squared) {
    //     normal_vec = v3_mult(normal_vec, -1.0); // Flip normal if camera inside
    // }


    // Calculate final color using existing lighting function
    return (calculate_lights(scene, hitpoint, normal_vec, cylobj));
}