# Builder stage
FROM ubuntu:22.04 AS builder

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    gcc \
    make \
    wget \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Valgrind 3.18.1
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 \
    && tar -xjf valgrind-3.18.1.tar.bz2 \
    && cd valgrind-3.18.1 \
    && ./configure \
    && make -j \
    && make -j install DESTDIR=/install \
    && cd .. \
    && rm -rf valgrind-3.18.1*

# Make 4.3
RUN wget http://ftp.gnu.org/gnu/make/make-4.3.tar.gz \
    && tar -xvzf make-4.3.tar.gz \
    && cd make-4.3 \
    && ./configure \
    && make -j \
    && make -j install DESTDIR=/install \
    && cd .. \
    && rm -rf make-4.3*


# Final stage
FROM ubuntu:22.04 AS final

# Install packages
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && apt-get install -y \
    # System utilities
    curl \
    git \
    gnupg \
    software-properties-common \
    sudo \
    wget \
    zsh \
    # Add LLVM and GCC repositories
    && wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
    && add-apt-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-12 main" \
    && add-apt-repository ppa:ubuntu-toolchain-r/test \
    && apt-get install -y \
    # Build tools and compilers
    binutils \
    build-essential \
    clang \
    clang-14 \
    clang-12 \
    cmake \
    gcc-11=11.4.0-1ubuntu1~22.04 \
    g++-11=11.4.0-1ubuntu1~22.04 \
    gcc-10=10.5.0-1ubuntu1~22.04 \
    g++-10=10.5.0-1ubuntu1~22.04 \
    meson \
    # Development tools
    clang-tools \
    clang-tools-12 \
    clangd \
    cppcheck \
    gdb \
    lldb-12 \
    valgrind \
    # User utilities
    ncdu \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Set up compiler aliases
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-12 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-12 100 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 100 \
    && update-alternatives --install /usr/bin/cc cc /usr/bin/clang-12 100 \
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-12 100

# Copy built artifacts from builder
COPY --from=builder /install /

# Configure default user and workspace paths
# These can be overridden at build time using --build-arg
ARG USERNAME=devcontainer
ARG UID=1000
ARG GID=1000

# Create the user
RUN groupadd --gid $GID $USERNAME \
    && useradd --uid $UID --gid $GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Set the default home directory
ARG HOME=/home/$USERNAME

# Install oh-my-zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Change ownership of installed tools to the new user
RUN chown -R $USERNAME:$USERNAME $HOME

# Change zsh history to append mode to avoid error messages
RUN echo "unsetopt HIST_SAVE_BY_COPY" >> /etc/zsh/zshrc

# Set the default user for the container
USER $USERNAME
ENV USER=$USERNAME

# Set the working directory in the container
ARG WORKSPACE_FOLDER=/app
WORKDIR "/${WORKSPACE_FOLDER#/}"

CMD ["/bin/zsh"]
