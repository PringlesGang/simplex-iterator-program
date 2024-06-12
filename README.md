# Simplex Table Iterator
A tool for automatically deriving the next simplex table iteration, with respect to the current state and the user-provided pivot.

This tool makes use of a custom fraction class, meaning all values operated on and displayed will be exact rational numbers; not imprecise floating point numbers.

# How to use
Build an executable using a C++11 compiler. Upon launching the compiled binary, you should be prompted to enter the amount of columns and rows of your table. Afterwards, you will be asked to supply values for each cell.

Once that is complete, you'll be able to perform any of the following commands:

### `p`: pivot
Provide the pivot coordinate, and it will calculate the next table pivoting around that cell.

### `n`: new table
Throw away the current table, and enter a brand new one.

### `s`: substitute cell
Provide a coordinate, and the value the corresponding cell needs to be changed to.

### `l`: print in LaTeX
Print out LaTeX code for the current table.

### `r`: reduce all fractions
Reduce all fractions in the table—dividing the numerator and denominator by their greatest common divisor.

### `q`: quit
Exit the program.

## Fraction format
This program uses genuine fractions; not approximated floating point values. These fractions can easily be entered in the following regex format: `-?[0-9]+(\/[1-9][0-9]*)?`. Intuitively, just provide a (possibly negative) numerator, followed by a slash, and then the denominator. Examples are:
- `1/2` $\mapsto \frac{1}{2}$;
- `-25/5` $\mapsto -\frac{25}{5} = -5$;
- `42` $\mapsto 42$;
- `-1048596/1097302` $\mapsto -\frac{1048596}{1097302} = -\frac{524298}{548651}$.

# Simplex pivot explanation
This tool aids in manually solving linear programming problems using the simplex method, as described in the _Combinatoriek en Optimalisering_ 2023 dictation, by L.C.M Kallenberg, F.M. Spieksma and M.J.H. van den Bergh as part of the decision theory courses of Leiden University's mathematics bachelor's program.

The program iterates simplex tables on the user-supplied pivot. It does so as follows:

Assume an $n \times n$ simplex table $(a\_{ij})\_{ij}$, indexed $1$ through $n$ with the top-left value being $(\text{column}, \text{row}) = (1,1)$.
The user supplies the coordinates $(c, r)$ of the pivot, around which will be iterated.
The $n \times n$ table $(b\_{ij})\_{ij}$ corresponding to the next iteration will have the following values:
- $b\_{ij} := a\_{ij} - \frac{a\_{cj}\ \cdot\ a\_{ir}}{a\_{cr}}$ for all $(i, j)$ with $i \neq c$ and $j \neq r$—outside of the pivot row and column;
- $b\_{cj} := -\frac{a\_{cj}}{a\_{cr}}$ for all $j \neq r$—in the pivot column but outside of the pivot row;
- $b\_{ir} := \frac{a\_{ir}}{a\_{cr}}$ for all $i \neq c$—in the pivot row but outside of the pivot column;
- $b\_{cr} := \frac{1}{a\_{cr}}$ for the pivot itself.

Along with this, the names corresponding to the pivot row and column will be swapped.
