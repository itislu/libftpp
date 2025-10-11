FROM debian:bullseye-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN echo "deb [trusted=yes] http://archive.debian.org/debian/ lenny main" > /etc/apt/sources.list.d/lenny.list

# Fix the broken postinst script of gcc-4.2-base
RUN mkdir -p /usr/share/doc/gcc-4.2-base && \
    touch /usr/share/doc/gcc-4.2-base/changelog.Debian.gz

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    gcc-4.2 \
    g++-4.2 \
    zsh \
    curl \
    git && \
    rm -rf /var/lib/apt/lists/*

RUN ln -s /usr/bin/gcc-4.2 /usr/local/bin/gcc && \
    ln -s /usr/bin/g++-4.2 /usr/local/bin/g++

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended

RUN chsh -s /bin/zsh

WORKDIR /workspace

CMD ["/bin/zsh"]
