{
  description = "Break Blocks";

  # Nixpkgs / NixOS version to use.
  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

  outputs = {nixpkgs, ...}: let
    inherit (nixpkgs) lib;
    # Get all supported systems by nixpkgs
    supportedSystems = lib.systems.flakeExposed;

    forEachSystem = f:
      lib.genAttrs supportedSystems (system: f pkgsFor.${system});
    pkgsFor = lib.genAttrs supportedSystems (system:
      import nixpkgs {
        inherit system;
        config.allowUnfree = true;
        config.allowUnfreePredicate = _: true;
      });
  in {
    # Provide some binary packages for selected system types.
    packages = forEachSystem (pkgs:
      with pkgs; {
        default = pkgs.stdenv.mkDerivation {
          name = "main";
          src = ./.;
          nativeBuildInputs = [cmake];
          buildInputs = [
            SDL2
            SDL2_ttf
            SDL2_net
            SDL2_gfx
            SDL2_sound
            SDL2_mixer
            SDL2_image
            SDL2_Pango
          ];
        };
      });
  };
}
