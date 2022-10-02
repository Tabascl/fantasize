pkgname=fantasize
pkgver=0.1.0
pkgrel=1
pkgdesc='C++ fan control for Linux'
url='https://github.com/Tabascl/fantasize.git'
source=("$pkgname-$pkgver.tar.gz::https://github.com/Tabascl/fantasize/archive/refs/tags/v$pkgver.tar.gz")
arch=('x86_64')
license=('GPL3')
makedepends=('git' 'cmake' 'nlohmann-json' 'boost' 'cuda')
sha256sums=('417705e0214c1f39dd8c9f06e97b6f1478c5808a2defe1fa0f1c6550bd15d6c5')

build() {
    cmake -S "$pkgname-$pkgver/app" -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
}

package() {
    cmake --install build --prefix "$pkgdir/" --verbose
}
