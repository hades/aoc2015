FROM archlinux:latest

RUN pacman -Sy

RUN pacman -S -q --noconfirm clang bazel libc++

ARG USERNAME=hades
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME

USER $USERNAME

ENV CC=clang
ENV USE_CLANG_CL=1
ENV BAZEL_CXXOPTS="-stdlib=libc++"
ENV BAZEL_LINKLIBS="-lc++:-lm:-lssl:-lcrypto"
