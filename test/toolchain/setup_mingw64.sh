##======================================================================================================================
##  SPY - C++ Informations Broker
##  Copyright : SPY Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
## Sourced by the matrix before configuring the mingw64 row. The Windows runner ships a MinGW-w64 g++ but leaves it
## out of PATH, and where it lives has moved between image versions, so the directory is looked up rather than named.
##======================================================================================================================
mingw_bin=""

for candidate in "${MINGW64_BIN}"                                                 \
                 "/c/msys64/mingw64/bin"                                          \
                 "/c/ProgramData/chocolatey/lib/mingw/tools/install/mingw64/bin"  \
                 "/c/mingw64/bin"
do
  if [[ -n "$candidate" && -x "$candidate/g++.exe" ]]; then
    mingw_bin="$candidate"
    break
  fi
done

if [[ -z "$mingw_bin" ]]; then
  probe="$(command -v g++ 2>/dev/null || true)"
  if [[ -n "$probe" ]]; then
    mingw_bin="$(dirname "$probe")"
  fi
fi

if [[ -z "$mingw_bin" ]]; then
  echo "No MinGW g++ found. Looked in /c/msys64/mingw64/bin," \
       "/c/ProgramData/chocolatey/lib/mingw/tools/install/mingw64/bin, /c/mingw64/bin and PATH." >&2
  return 1 2>/dev/null || exit 1
fi

export PATH="$mingw_bin:$PATH"

## A g++ that is not a MinGW one would build a target spy reports as something else, so the failure is made loud here
## rather than left to a unit test on another platform.
target="$(g++ -dumpmachine)"
case "$target" in
  *mingw*) ;;
  *) echo "g++ in $mingw_bin targets $target, which is not MinGW." >&2
     return 1 2>/dev/null || exit 1 ;;
esac

## CMake reads this one, and the following steps of the job get the directory through GITHUB_PATH.
export MINGW64_BIN="$(cygpath -m "$mingw_bin" 2>/dev/null || echo "$mingw_bin")"
if [[ -n "$GITHUB_PATH" ]]; then
  echo "$MINGW64_BIN" >> "$GITHUB_PATH"
fi

echo "Using $(g++ --version | head -1) from $MINGW64_BIN"
