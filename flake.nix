{
  description = "JustFetch - suckless system info fetch tool";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    packages.${system}.default = pkgs.stdenv.mkDerivation {
      pname = "jf";
      version = "0.1.0";
      src = self;
      buildInputs = [ pkgs.stdenv.cc ];
      buildPhase = "make";
      installPhase = ''
        runHook preInstall
        install -Dm755 jf $out/bin/jf
        runHook postInstall
      '';
    };
  };
}