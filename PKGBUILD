pkgname=fantasize
pkgver=0.1.0
pkgrel=1
pkgdesc='C++ fan control for Linux'
url='https://github.com/Tabascl/fantasize.git'
source=("$pkgname-$pkgver.tar.gz::https://github.com/Tabascl/fantasize/archive/refs/tags/v$pkgver.tar.gz")
arch=('x86_64')
license=('GPL3')
makedepends=('git' 'cmake' 'nlohmann-json' 'boost' 'cuda')
sha256sums=('e3bb758e96b816b417212eeeb20eaebebbc6dc976276ca5d70074e4df64aaa95')

build() {
    cmake -S "$pkgname-$pkgver/app" -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
}

package() {
    cmake --install build --prefix "$pkgdir/" --verbose
}
