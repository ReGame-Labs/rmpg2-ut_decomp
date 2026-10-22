# The CI runner's environment (ubuntu-24.04, as .github/workflows/ci.yml's jobs) for running the checks locally
# before a push: scripts/ci_local.sh builds this image and runs scripts/test.sh in it, with the tools built by
# scripts/setup.sh kept in a Docker volume between runs and the game files mounted read-only.
#
# The image holds no game data and no tools: only the packages the toolchain is built with.
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive LANG=C.UTF-8
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
        build-essential ca-certificates cmake curl file git ninja-build python3 python3-venv unzip xz-utils \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /work
