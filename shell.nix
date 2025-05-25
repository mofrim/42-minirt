{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  name = "minirt";

  buildInputs = with pkgs; [
    clang-tools
    clang_12
    libbsd
    xorg.libXext
    xorg.libX11.dev
    qt5.qtwayland
    xorg.fontmiscmisc
    xlsfonts
    xorg.xset
  ];

  shellHook = ''
    export NIX11="${pkgs.xorg.libX11.dev}/include"
    export QT_QPA_PLATFORM=wayland
    xset +fp "${pkgs.xorg.fontmiscmisc.out}/lib/X11/fonts/misc"
  '';
}
