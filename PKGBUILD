pkgname=fantasize
pkgver=0.3.0
pkgrel=1
pkgdesc='C++ fan control for Linux'
url='https://github.com/Tabascl/fantasize.git'
source=("$pkgname-$pkgver.tar.gz::https://github.com/Tabascl/fantasize/archive/refs/tags/v$pkgver.tar.gz")
arch=('x86_64')
license=('GPL3')
makedepends=('git' 'meson' 'nlohmann-json' 'boost')
sha256sums=('SKIP')

build() {
    meson setup build "$pkgname-$pkgver/app" -Dbuildtype=Release
    cd build
    meson compile
}

package() {
    cd build
    meson install
}
