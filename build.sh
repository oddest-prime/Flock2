cmake CMakeLists.txt \
    -DLIBMIN_ROOT=../libmin \
    -B../build/Flock2 \
    -DBUILD_CUDA=false \
    -DBUILD_OPENGL=true \
    -DBUILD_GLEW=true

make -C../build/Flock2
