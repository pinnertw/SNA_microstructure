# SNA_microstructure

We try to modelize the ruin of a bank with the microstructure of the market. The project corresponds to the 8th question in [here](../blob/master/ProjectMODAL_SNAX18.pdf).

First of all, we try to modelize the prices with a difference of {+1, -1, ..., +m, -m} with a certain probability for each price. Then we consider the probatility of the ruin with the Monte-Carlo method. Moreover, we have implemented the model [here](../blob/master/FodraPhamMicrostructure2015.pdf)

The C++ directory includes the implementation in C++ in a much more efficient way.
