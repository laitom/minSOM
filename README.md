# minSOM

A simple implementation of the self-organizing map. The implementation is based on the description of SOM given by Kohonen in chapter 3 of his book _Self-Organizing Maps_. This is mostly a personal study on how the algorithm can be implemented and not meant to be a viable way for someone to analyze large datasets.

## Model/reference vector initialization

The model vectors for each of the nodes on the map are initialized at random between two arbitrarily chosen values. A more practical initialization method would be to initialize the model components with randomly selected values from the input vector components.

## Neighborhood function

The neighborhood used in the map is a simple neighborhood set (aka the bubble function), as described by Kohonen in his book. The initial radius of the neighborhood is set to approximately half the distance between the two corners of the map, and the radius of the neighborhood is decremented by one every 1000 training cycles. Another common neighborhood function is the Gaussian function.

## Learning rate factor

The learning rate factor (alpha) is a linearly decreasing function of the training cycle number.

## Best-matching node

The best matching node for every input vector is calculated in a common way, by selecting the node that minimizes the Euclidean distance.

## The learning process

The input vectors are projected onto the map one by one, and the models of the nodes in the neighborhood around the node with the best-matching model (as well as the node with the best-matching model itself) are smoothed with the input vector.