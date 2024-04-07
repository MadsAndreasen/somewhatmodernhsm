FROM ubuntu:23.10

RUN apt update && apt install -y --no-install-recommends software-properties-common wget curl gnupg

RUN apt update && apt install -y --no-install-recommends \
                                                         python3 python3-pip pipx git python-is-python3 \
                                                         sudo ninja-build build-essential fish gcovr lcov llvm

RUN echo 'ubuntu ALL=(ALL) NOPASSWD: ALL' > /etc/sudoers.d/ubuntu
USER ubuntu

RUN pipx install meson

ENV PATH="/root/.local/bin/:${PATH}"
