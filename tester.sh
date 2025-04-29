#!/usr/bin/env bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 18:59:18 by fmaurer           #+#    #+#              #
#    Updated: 2025/04/29 18:59:18 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# quick and dirty tester for invalid minirt scenefiles

TESTDIR=./rtfiles/testing/malformed-rtfiles

if [ ! -e ./minirt ]; then
	echo ">>> minirt not found!"
	exit 1
fi

if [ ! -e $TESTDIR ]; then
	echo ">>> test dir not found!"
	exit 1
fi

if [ "$(ls -1 $TESTDIR | wc -l)" -eq 0 ]; then
	echo ">>> testdir empty!"
	exit 1
fi

for i in $(ls -1 $TESTDIR); do
	if [ ! "$(echo $i | cut -f 1 -d '_')" = "TEMPLATE" ]; then
		echo ">>> testing file $TESTDIR/$i:"
		echo "---"
		./minirt $TESTDIR/$i > /dev/null
		echo "---"
		echo ">>> done testing file $i."
		read -r
	fi
done



