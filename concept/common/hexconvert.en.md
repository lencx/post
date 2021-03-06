# Hex convert

| Number literals | example |
| --------------- | ------- |
| Decimal         | 999     |
| Hex             | 0xff    |
| Octal           | 0o85    |
| Binary          | 0b10010 |

| Binary | Decimal | Hex |     | Binary    | Decimal | Hex |
| ------ | ------- | --- | --- | --------- | ------- | --- |
| 0      | 0       | 0   |     | 10000     | 16      | 10  |
| 1      | 1       | 1   |     | 10001     | 17      | 11  |
| 10     | 2       | 2   |     | 10010     | 18      | 12  |
| 11     | 3       | 3   |     | 10011     | 19      | 13  |
| 100    | 4       | 4   |     | 10100     | 20      | 14  |
| 101    | 5       | 5   |     | 10101     | 21      | 15  |
| 110    | 6       | 6   |     | 10110     | 22      | 16  |
| 111    | 7       | 7   |     | 10111     | 23      | 17  |
| 1000   | 8       | 8   |     | 11000     | 24      | 18  |
| 1001   | 9       | 9   |     | 11001     | 25      | 19  |
| 1010   | 10      | A   |     | 11010     | 26      | 1A  |
| 1011   | 11      | B   |     | 11111     | 31      | 1F  |
| 1100   | 12      | C   |     | 100000    | 32      | 20  |
| 1101   | 13      | D   |     | 1000000   | 64      | 40  |
| 1110   | 14      | E   |     | 10000000  | 128     | 80  |
| 1111   | 15      | F   |     | 100000000 | 256     | 100 |

## Binary -> Decimal

For binary number with n digits:
<!-- > $d_{n-1}...d_3d_2d_1d_0$ -->
> d<sub>n-1</sub>...d<sub>3</sub>d<sub>2</sub>d<sub>1</sub>d<sub>0</sub>

The decimal number is equal to the sum of binary digits (<!--$d_n$-->d<sub>n</sub>) times their power of 2 (2<sup>n</sup>)
<!-- > decimal = $d_0×2^0+d_1×2^1+d_2×2^2+...$ -->
> decimal = d<sub>0</sub>×2<sup>0</sup>+d<sub>1</sub>×2<sup>1</sup>+d<sub>2</sub>×2<sup>2</sup>+...

---

Example

Find the decimal value of <!-- $111001_2$ -->111001<sub>2</sub>

|                   |       |       |       |       |       |       |
| ----------------- | ----- | ----- | ----- | ----- | ----- | ----- |
| **binary number** | 1     | 1     | 1     | 0     | 0     | 1     |
| **power of 2**    | 2<sup>5</sup> | 2<sup>4</sup> | 2<sup>3</sup> | 2<sup>2</sup> | 2<sup>1</sup> | 2<sup>0</sup> |

<!-- | **power of 2**    | $2^5$ | $2^4$ | $2^3$ | $2^2$ | $2^1$ | $2^0$ | -->

<!-- > $111001_2 = 1⋅2^5+1⋅2^4+1⋅2^3+0⋅2^2+0⋅2^1+1⋅2^0 = 57_{10}$ -->
> 111001<sub>2</sub> = 1⋅2<sup>5</sup>+1⋅2<sup>4</sup>+1⋅2<sup>3</sup>+0⋅2<sup>2</sup>+0⋅2<sup>1</sup>+1⋅2<sup>0</sup> = 57<sub>10</sub>