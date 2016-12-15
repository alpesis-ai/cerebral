sudo apt-get install -y cmake
sudo apt-get install build-essential

# -----------------------------------------------------
# armadillo
cd lib/armadillo
mkdir build
cmake ..
sudo make install

sudo apt-add-repository ppa:comp-phys/stable
sudo apt-get update
sudo apt-get install libarmadillo-dev

# -----------------------------------------------------
