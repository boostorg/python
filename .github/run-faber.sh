#!/bin/sh

set -eu

echo "cxx version: $CXX $($CXX --version)"
echo "cxx std: $CXX_STD"
echo "python3 path: $(which python3)"
echo "python3 version: $(python3 --version)"

if ! which faber > /dev/null; then
    echo "Installing faber..."
    python3 -m pip install --upgrade pip
    python3 -m pip install -U faber
fi
echo "faber version: $(faber -v)"

# find and set PY_LDFLAGS and PY_INC_PATH
eval $(python3 .github/get-py-env.py)

echo "PY_INC_PATH=$PY_INC_PATH"
echo "PY_LDFLAGS=$PY_LDFLAGS"

case $(python3-config --abiflags) in
    *t*)
        # When running with free-threaded, we always want to disable the GIL
        # even for extensions without the mod_gil_not_used() flag
        export PYTHON_GIL=0
        ;;
esac

# this could be set by LD_LIBRARY_PATH but faber overrides it
prefix=$(python3-config --prefix)
echo "${prefix}/lib" > /etc/ld.so.conf.d/boost-ci.conf && ldconfig

sed -e "s/\$PYTHON/python3/g" .ci/faber > $HOME/.faber

faber \
  --with-boost-include=${BOOST_PY_DEPS} \
  --builddir=build \
  cxx.name="${CXX}" \
  cxxflags="-std=${CXX_STD}" \
  cppflags="-std=${CXX_STD}" \
  include="${PY_INC_PATH}" \
  ldflags="${PY_LDFLAGS}" \
  -j`nproc` \
  "$@"
