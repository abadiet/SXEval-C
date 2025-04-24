# SXEval
S-expression interpreter

## Usage
```bash
mkdir build
cd build
cmake ..
make
./examples/examples_basic '(* 2 x (+ 2.3 x) -4.1 (* 2 2 1.2) 3)'
```
```bash
Parsed expression: (* 2 x (+ 2.3 x) -4.1 (* 2 2 1.2) 3)
Result: -4309.920000
```

### Options
- ```BUILD_EXAMPLES```: Build examples
- ```UPDATE_SUBMODULES```: Update and download submodules
- ```SXEVAL_DEBUG```: Print debug informations

## Dependencies
- [uthash](https://troydhanson.github.io/uthash/): included as a submodule
- [sfsexp](https://github.com/mjsottile/sfsexp): included as a submodule
