# CPP_09
STL



# PmergeMe

it is the implementation of a sequencing algorithm.

In the [The art of programming. Volume 3 sorting and searching](https://seriouscomputerist.atariverse.com/media/pdf/book/Art%20of%20Computer%20Programming%20-%20Volume%203%20(Sorting%20&%20Searching).pdf) i read about why programers selected the "sort" word for sequencing elements.

Two sentences in the book called my attention
"Since only two of our tape drives were in **working order**, I was **ordered** to **order** more tape units in **short order**, **in order** to **order** the data several **orders** of magnitude faster."

"Since only two of our tape drives were **operational**, I was **instructed** to **procure** more tape units **quickly**, *so that we could **sort** the data several **degrees** of magnitude faster."


"I was **sort of** **out of sorts** after **sorting** that **sort** of data"

"I was **somewhat** **unwell** after **organizing** that **type** of data."

### Mathematically what is sorting?


The records:
```math
R_1, R_2, \ldots, R_n
```
 are supposed to be sorted into nondecreasing order of their keys

 ```math 
 K_1, K_2, \ldots, K_n
 ```
 
essentially by discovering a permutation 

```math
p(1), p(2), \ldots, p(N)
```
such that

```math
K_{p(1)} \le K_{p(2)} \le \ldots \le K_{p(N)}
```

Before the algorithm we must implement i found:
+ Sorting by counting. Counting how many elements one exceeds gives element's position in final permutation.

+ Internal sorting
    + Sorting by insertion.
        + Stright insertion  (sinking sort).
        + Binary insertion.
        + Two-way insertion.
        + Shell Sort[pag 83].
        + List Insertion.
        + Address Calculation Sorting.
    + Sorting by Exchanging.
        + Exchange Selection (The bubble Sort).
            +Batcher's parallel method.
        + Quicksort.
        + Radix Exchange.
    + Sorting by selection.
        + Straight selection.
        + Tree Selection.
        + Heapsort.
            + Largest in, first out. (priority queues)
    + Sorting by Merging.
        + Two-way merge.
        + Natural two-way merger sort.
        + Straight two-way merger sort.
        + List merge sort.
    + Sorting by distribution
        + Radix list sort.
        + Hooking-up of queues.

+ Optimum Sorting.

Aim: minimizing comparisons.
    winners: binary insertion, tree selection, straight two-way merging.



## subject requirements

Your program must be able to handle at least 3000 **different** integers.
a set is a candidate
