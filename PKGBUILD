pkgname=fantasize
pkgver=0.1.7
pkgrel=1
pkgdesc='C++ fan control for Linux'
url='https://github.com/Tabascl/fantasize.git'
source=("$pkgname-$pkgver.tar.gz::https://github.com/Tabascl/fantasize/archive/refs/tags/v$pkgver.tar.gz")
arch=('x86_64')
license=('GPL3')
makedepends=('git' 'cmake' 'nlohmann-json' 'boost' 'cuda')
sha256sums=('SKIP')

build() {
    cmake -S "$pkgname-$pkgver/app" -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
}

package() {
    cmake --install build --prefix "$pkgdir/" --verbose
}
