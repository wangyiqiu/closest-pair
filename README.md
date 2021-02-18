# Parallel Dynamic and Static Euclidean Closest-Pair
## About

This repository contains code for our SoCG'21 paper (to appear): A Parallel Batch-Dynamic Data Structure for the Closest Pair Problem ([arXiv](https://arxiv.org/abs/2010.02379)). It contains fast code for a parallel batch-dynamic data structure that maintains the Euclidean closest pair, as well as four parallel implementations of the static closest pair problem (based on Rabin's randomized algorithm, the divide-and-conquer algorithm, the sieve algorithm, and the incremental algorithm).

## Data set

We included a small example data set in the `closest-pair/data` folder. We include larger data sets at this [dropbox link](https://www.dropbox.com/sh/ehhv9thpuvb36jq/AADQowvv9FfQ8ZYdAPL9qJs1a?dl=0). More data sets also can be generated using the data generator in [pbbsbench](https://github.com/cmuparlay/pbbsbench/tree/master/testData/geometryData). A data set in the same format will also work, as long as they have a header `pbbs_sequencePoint<k>d`, where `<k>` specifies the dimensionality, a number between 2 and 9 inclusive, followed by lines of space-delimited point coordinates.

## Running the dynamic code

To compile the code, navigate to `closest-pair/dynamicClosestPair/dynamic/`, and input `make clean` first. For serial execution, just `make`; for parallel execution, use `CILK=1 make`; for the most optimal parallel performance, install [jemalloc](https://github.com/jemalloc/jemalloc/blob/dev/INSTALL.md) first and then use `CILK=1 USEJEMALLOC=1 make`.

To run the code,
```
./closestPair -b 10 ../../data/2D_UniformFill_10K.pbbs
```
where `-b <batch>` specifies the program to dynamically insert the data set in `<batch>` batches, and then remove them in `<batch>` batches. The `main` function starts from line 772 of `closest-pair/dynamicClosestPair/dynamic/closestPair.C`, which can be modified for other functionalities.

## Running the static code

To compile the code, navigate to `closest-pair/closestPair/rabin`, and input `make clean` first. For serial execution, just `make`; for parallel execution, use `CILK=1 make`; for the most optimal parallel performance, install [jemalloc](https://github.com/jemalloc/jemalloc/blob/dev/INSTALL.md) first and then use `CILK=1 USEJEMALLOC=1 make`.

To run the code,
```
./closestPair ../../data/2D_UniformFill_10K.pbbs
```
The program will use Rabin's algorithm to solve the closest pair, and it can be done similarly for the rest of the algorithms in the following directories: `closest-pair/closestPair/divideConquer`, `closest-pair/closestPair/sieve` and `closest-pair/closestPair/incremental`.

## Support

Please feel free to contact the developers or the paper authors if you encounter any problems, we are happy to patch/fix the program.

## Citation

If you use our work in a publication, we would appreciate citations:

    @misc{wang2020parallel,
          title={A Parallel Batch-Dynamic Data Structure for the Closest Pair Problem}, 
          author={Yiqiu Wang and Shangdi Yu and Yan Gu and Julian Shun},
          year={2020},
          eprint={2010.02379},
          archivePrefix={arXiv},
          primaryClass={cs.DS}
    }
