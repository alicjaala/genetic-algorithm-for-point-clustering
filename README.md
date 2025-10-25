# GA-Cluster: A GeneticAlgorithm for Point Clustering

A C++ implementation of a classic Genetic Algorithm (GA) designed to solve the point clustering optimization problem.


## 🧩 The Optimization Problem

The algorithm is tasked with solving a point clustering problem. The goal is to assign $n$ points to $k$ available groups in such a way that the **sum of Euclidean distances** between points within the same group is **minimized**.

The evaluation (fitness) function is provided by an external framework (the `dEvaluate` method within the `CGroupingEvaluator` object).

## 🧬 Genetic Algorithm Implementation

The algorithm operates based on the evolution of a population of potential solutions (individuals) over successive generations.

### 1. Individual (Genotype)

A single solution (individual) is encoded as an array of $n$ integers, where $n$ is the number of points. The value at the $i$-th index of the array represents the group ID assigned to the $i$-th point.

*Example for n=4 points and k=3 groups:* `[1, 3, 3, 2]`

### 2. Algorithm Flow

1.  **Initialization**: An initial population of `PopSize` random individuals is generated. Each gene (point) is assigned a random group ID from 1 to $k$.
2.  **Evaluation**: The fitness value for each individual in the population is calculated using the provided `dEvaluate` method.
3.  **Selection (Tournament)**: A new population is created. To select a parent, two individuals are randomly sampled from the current population, and the one with the better (lower) fitness is chosen. This process is repeated to select pairs of parents.
4.  **Crossover (Single-Point)**:
    * For each pair of parents, crossover occurs with a probability of `CrossProb`.
    * A single crossover point (from 1 to $n-1$) is randomly selected.
    * Two "children" are produced by exchanging the genetic material (genotypes) of the parents at the crossover point.
    * If crossover does not occur (with probability $1 - CrossProb$), exact copies of the parents are passed to the new population.
5.  **Mutation**:
    * Every individual in the newly created population undergoes mutation.
    * Each individual gene (a point's group assignment) within the genotype is mutated with a probability of `MutProb`.
    * A mutation consists of replacing the gene's current value with a new, randomly selected group ID.
6.  **Termination Condition**: The algorithm returns to step 2 unless a stopping criterion is met (e.g., time limit exceeded, a set number of iterations completed, or a limit on evaluation function calls reached).

## 🏛️ Code Architecture

As per the assignment requirements, the implementation is centered around two primary classes:

### `CIndividual`

* Represents a single individual (solution).
* Stores the genotype (e.g., in `std::vector<int>`).
* Stores its calculated fitness value.
* Is responsible for the logic of operations on a single individual:
    * **Evaluation Method**: Calls the external evaluator to calculate and store its own fitness.
    * **Mutation Method**: Mutates its own genotype based on `MutProb`.
    * **Crossover Method**: Accepts another individual (`CIndividual& other`) and returns a pair of new individuals (`std::pair<CIndividual, CIndividual>`) resulting from the crossover operation.

### `CGeneticAlgorithm`

* The main class that manages the algorithm's execution flow.
* Stores the runtime parameters (`PopSize`, `CrossProb`, `MutProb`).
* Manages the entire population of individuals (e.g., `std::vector<CIndividual>`).
* Is responsible for the main algorithm loop (evolution).
* Implements the tournament selection logic.
* Tracks the best solution found throughout the algorithm's history.
* Provides a method to retrieve the best solution after the run is complete.

This project is designed to be integrated with the provided framework (which includes the CGroupingEvaluator class).
