{
  description = "A C++ sandbox development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            # Compilers and standard libraries
            gcc
            clang
            linuxHeaders
            
            # Build systems
            cmake
            ninja
            meson
            pkg-config
            
            # Development tools
            gdb
            lldb
            valgrind
            
            # Code analysis and formatting
            clang-tools  # includes clang-format, clang-tidy, etc.
            cppcheck
            
            # Libraries (commonly used)
            boost
            fmt
            spdlog
            catch2
            gtest

            # Documentation
            doxygen
            graphviz
            
            # Optional: Language servers for IDE support
            # clangd is included in clang-tools above
            bear    # For generating compile_commands.json
          ];

          # Environment variables
          shellHook = ''
            echo "🚀 C++ Development Environment"
            echo "Compilers: gcc $(gcc --version | head -n1), clang $(clang --version | head -n1)"
            echo "Build tools: cmake $(cmake --version | head -n1), ninja $(ninja --version)"
            echo ""
            echo "Available tools:"
            echo "  - Build: cmake, ninja, meson"
            echo "  - Debug: gdb, lldb, valgrind"
            echo "  - Analysis: clang-tidy, cppcheck"
            echo "  - Format: clang-format"
            echo "  - Test: catch2, gtest"
            echo "  - Docs: doxygen"
            echo ""
            
            # Set up some useful aliases
            alias ll='ls -la'
            alias build='mkdir -p build && cd build && cmake .. && make -j$(nproc)'
            alias clean='rm -rf build'
            alias bear-make='bear -- make'
            alias nvim-here='nvim .'
            
            # Generate compile_commands.json for LSP
            alias gen-compile-commands='cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build'
            
            # Ensure C++ headers are found - simplified for nix-ld systems
            export NIX_CC_WRAPPER_TARGET_HOST_x86_64_unknown_linux_gnu=1
            export NIX_CC_WRAPPER_x86_64_unknown_linux_gnu_TARGET_HOST=1
            
            # Standard library paths for nix-ld compatibility
            export C_INCLUDE_PATH="${pkgs.glibc.dev}/include:${pkgs.linuxHeaders}/include:$C_INCLUDE_PATH"
            export LIBRARY_PATH="${pkgs.glibc}/lib:${pkgs.gcc.cc.lib}/lib:$LIBRARY_PATH" 
            
            # For clangd LSP - use system detection with query-driver
            export CLANGD_FLAGS="--header-insertion=never --compile-commands-dir=build --query-driver=${pkgs.gcc}/bin/gcc,${pkgs.gcc}/bin/g++,${pkgs.clang}/bin/clang,${pkgs.clang}/bin/clang++"
            
            # Create a .clangd config file that works with nix-ld and query-driver
            cat > .clangd << EOF
CompileFlags:
  Add:
    - -std=c++20
  CompilationDatabase: build
Index:
  Background: Build
EOF

            # Create a wrapper script for clangd that includes query-driver and system headers
            cat > clangd-wrapper << 'WRAPPER_EOF'
#!/usr/bin/env bash
export CPLUS_INCLUDE_PATH="${pkgs.gcc}/include/c++/${pkgs.gcc.version}:${pkgs.gcc}/include/c++/${pkgs.gcc.version}/x86_64-unknown-linux-gnu:${pkgs.glibc.dev}/include:${pkgs.linuxHeaders}/include:$CPLUS_INCLUDE_PATH"
export C_INCLUDE_PATH="${pkgs.glibc.dev}/include:${pkgs.linuxHeaders}/include:$C_INCLUDE_PATH"
exec ${pkgs.clang-tools}/bin/clangd \
  --query-driver=${pkgs.gcc}/bin/gcc,${pkgs.gcc}/bin/g++,${pkgs.clang}/bin/clang,${pkgs.clang}/bin/clang++ \
  --header-insertion=never \
  --compile-commands-dir=build \
  --background-index \
  --clang-tidy \
  "$@"
WRAPPER_EOF
            chmod +x clangd-wrapper
            
            echo "Created clangd-wrapper script with query-driver support"
            echo "In Neovim LSP config, use: $(pwd)/clangd-wrapper as the command"
            echo ""
            echo "Testing header availability..."
            echo '#include <stdlib.h>' | ${pkgs.gcc}/bin/gcc -E -x c - >/dev/null 2>&1 && echo "✓ C headers found" || echo "✗ C headers missing"
            echo '#include <iostream>' | ${pkgs.gcc}/bin/g++ -E -x c++ - >/dev/null 2>&1 && echo "✓ C++ headers found" || echo "✗ C++ headers missing"
            
            # Set C++ standard (adjust as needed)
            export CXXFLAGS="-std=c++20"
          '';

          # Environment variables for development
          CMAKE_BUILD_TYPE = "Debug";
          # Let nix-ld handle the compiler paths
          CC = "gcc";
          CXX = "g++";
        };

        # Optional: Add packages that can be built
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "sandbox";
          version = "0.1.0";
          
          src = ./.;
          
          nativeBuildInputs = with pkgs; [
            cmake
            ninja
          ];
          
          buildInputs = with pkgs; [
            boost
            fmt
            spdlog
          ];
          
          configurePhase = ''
            cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
          '';
          
          buildPhase = ''
            cmake --build build
          '';
          
          installPhase = ''
            mkdir -p $out/bin
            cp build/* $out/bin/ || true
          '';
        };
      });
}
