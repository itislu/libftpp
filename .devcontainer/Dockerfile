# Start from Ubuntu 22.04 (Jammy Jellyfish)
FROM ubuntu:22.04

# Add LLVM and GCC repositories
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && apt-get -y install \
    wget \
    gnupg \
    software-properties-common \
    && wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
    && add-apt-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-12 main" \
    && add-apt-repository ppa:ubuntu-toolchain-r/test

# Install packages including specific versions
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && apt-get -y install \
    wget \
    build-essential \
    cmake \
    cppcheck \
    valgrind \
    clang-12 \
    lldb-12 \
    gdb \
    gcc-10=10.5.0-1ubuntu1~22.04 \
    g++-10=10.5.0-1ubuntu1~22.04 \
    clangd \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Set up compiler aliases
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-12 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-12 100 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 100 \
    && update-alternatives --install /usr/bin/cc cc /usr/bin/clang-12 100 \
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-12 100

# Valgrind 3.18.1
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 \
    && tar -xjf valgrind-3.18.1.tar.bz2 \
    && cd valgrind-3.18.1 \
    && ./configure \
    && make \
    && make install \
    && ldconfig	\
    && cd .. \
    && rm -rf valgrind-3.18.1*

# Make 4.3
RUN wget http://ftp.gnu.org/gnu/make/make-4.3.tar.gz \
    && tar -xvzf make-4.3.tar.gz \
    && cd make-4.3 \
    && ./configure \
    && make \
    && make install \
    && cd .. \
    && rm -rf make-4.3*
