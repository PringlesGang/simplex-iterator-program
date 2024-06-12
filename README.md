# Simplex Table Iterator
A tool for automatically deriving the next simplex table iteration, with respect to the current state and the user-provided pivot.

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