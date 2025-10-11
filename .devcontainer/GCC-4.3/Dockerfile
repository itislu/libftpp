FROM debian:bullseye-slim

ENV DEBIAN_FRONTEND=noninteractive

# Add Lenny archive and disable signature checks
RUN echo "deb [trusted=yes] http://archive.debian.org/debian/ lenny main" > /etc/apt/sources.list.d/lenny.list && \
    mkdir -p /usr/share/doc/gcc-4.3-base && \
    touch /usr/share/doc/gcc-4.3-base/changelog.Debian.gz

# Install modern dependencies first
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        curl wget ca-certificates zsh git \
        libc6-dev && \
    rm -rf /var/lib/apt/lists/*

# Download Lenny packages
WORKDIR /tmp/lenny
RUN wget http://archive.debian.org/debian/pool/main/g/gcc-4.3/gcc-4.3_4.3.2-1.1_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/g/gcc-4.3/cpp-4.3_4.3.2-1.1_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/g/gcc-4.3/g++-4.3_4.3.2-1.1_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/g/gcc-4.3/gcc-4.3-base_4.3.2-1.1_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/g/gcc-4.3/libstdc++6_4.3.2-1.1_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/g/gcc-4.3/libstdc++6-4.3-dev_4.3.2-1.1_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/g/gcc-4.3/libgomp1_4.3.2-1.1_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/g/gmp/libgmp3c2_4.2.2+dfsg-3_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/m/mpfr/libmpfr1ldbl_2.3.1.dfsg.1-2_amd64.deb && \
    wget http://archive.debian.org/debian/pool/main/b/binutils/binutils_2.18.1~cvs20080103-7_amd64.deb

# Install in dependency-safe order
RUN dpkg -i gcc-4.3-base_*.deb && \
    dpkg -i \
        libgmp3c2_*.deb \
        libmpfr1ldbl_*.deb \
        binutils_*.deb \
        libstdc++6_*.deb && \
    dpkg -i \
        libstdc++6-4.3-dev_*.deb \
        cpp-4.3_*.deb \
        g++-4.3_*.deb \
        gcc-4.3_*.deb \
        libgomp1_*.deb && \
    dpkg --configure -a

# Symlink compilers
RUN ln -s /usr/bin/gcc-4.3 /usr/local/bin/gcc && \
    ln -s /usr/bin/g++-4.3 /usr/local/bin/g++

# Install Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended

# Set default shell
RUN chsh -s /bin/zsh

WORKDIR /workspace
CMD ["/bin/zsh"]
