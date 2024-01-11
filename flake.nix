{
  description = "Flake with shell for sk2 Project";
  #this project is about creating a simple java project with rest api
  #it allows to sort provided data using different algorithms and return sorted data though rest api

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }@inputs:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.x86_64-linux.default =
        pkgs.mkShell {

          shellHook = ''
            echo "Hello in sk2 development envirament"
            echo "nix develop"
          '';

          packages = with pkgs; [
            cmake
            bash
            gpp
            gcc
            clang-tools_17
            git
          ];
        };
    };
}
