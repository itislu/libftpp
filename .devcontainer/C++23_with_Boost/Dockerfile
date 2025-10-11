FROM gcc:13.2.0

# Add LLVM repository
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
    && echo "deb http://apt.llvm.org/bookworm/ llvm-toolchain-bookworm-19 main" >> /etc/apt/sources.list.d/llvm.list

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    clang-19 \
    gdb \
    git \
    libboost-all-dev \
    libc++-19-dev \
    libc++abi-19-dev \
    valgrind \
    zsh \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Configure clang
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-19 100 \
    --slave /usr/bin/clang++ clang++ /usr/bin/clang++-19

# Install Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended

# Set zsh as the default shell
RUN chsh -s /bin/zsh
