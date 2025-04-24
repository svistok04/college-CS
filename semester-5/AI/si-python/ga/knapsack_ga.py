import numpy as np
import time

class knapsackGA:
    def __init__(self, v, c, C, m=1000, T=100, crossover_type='one_point', selection_name='roulette', crossover_prob=0.5,
                 mutation_prob=0.01, la=0, elitism=False):
        self.v = v
        self.c = c
        self.C = C

        self.m = m
        self.T = T
        self.crossover_type = crossover_type
        self.selection_name = selection_name
        self.crossover_prob = crossover_prob
        self.mutation_prob = mutation_prob
        self.la = la
        self.elitism = elitism

        self.pop = np.random.randint(0, 2, size=(m, len(v)))
        self.fitness_history = []


    def __str__(self):
        txt = ''
        return txt

    def run(self):
        self.selection_ = getattr(knapsackGA, 'selection_' + self.selection_name)
        self.crossover_ = getattr(knapsackGA, 'crossover_' + self.crossover_type)

        for generation in range(self.T):
            fitness_scores = self.fitness_func()

            best_index = np.argmax(fitness_scores)
            best_individual = self.pop[best_index]
            best_fitness = fitness_scores[best_index]
            self.fitness_history.append(best_fitness)

            probabilities = self.selection_(self)
            selected_indices = np.random.choice(range(self.m), size=self.m, p=probabilities)
            selected_individuals = self.pop[selected_indices]

            new_pop = []
            for i in range(0, self.m, 2):
                parent1 = selected_individuals[i]
                parent2 = selected_individuals[(i + 1) % self.m]

                if np.random.rand() <= self.crossover_prob:
                    child1, child2 = self.crossover_(self, parent1, parent2)
                else:
                    child1, child2 = parent1, parent2

                new_pop.extend([child1, child2])

            new_pop = [self.mutation(ind) for ind in new_pop]

            if self.elitism:
                worst_index = np.argmin(fitness_scores)
                new_pop[worst_index] = best_individual

            self.pop = np.array(new_pop)

        fitness_scores = self.fitness_func()
        best_index = np.argmax(fitness_scores)
        print(f'this index was... {best_index}')
        print(f'this score was... {fitness_scores[best_index]}')
        return self.pop[best_index]


    def fitness_func(self):
        total_values = np.sum(self.pop * self.v, axis=1)
        total_weights = np.sum(self.pop * self.c, axis=1)
        if self.la == 0:
            scores = np.where(total_weights <= self.C, total_values, 0)
        elif self.la > 0:
                scores = total_values - self.la * np.maximum(0, total_weights - self.C, dtype=np.float64) ** 2
        else:
            raise ValueError("Penalty factor 'la' must exist as > 0 or left as 0")

        return scores

    def selection_roulette(self):
        scores = self.fitness_func()
        return scores / np.sum(scores)

    def selection_ranking(self):
        return 2 * (np.argsort(np.argsort(self.fitness_func())) + 1) / (self.m * (self.m + 1))

    def crossover_one_point(self, parent1, parent2):
        point = np.random.randint(1, len(parent1) - 1)
        child1 = np.concatenate((parent1[:point], parent2[point:]))
        child2 = np.concatenate((parent2[:point], parent1[point:]))
        return child1, child2

    def crossover_two_point(self, parent1, parent2):
        # point1 = 0
        # point2 = 0
        # while point1 >= point2:
        #     point1 = np.random.randint(1, len(parent1) - 1)
        #     point2 = np.random.randint(1, len(parent2) - 1)
        point1, point2 = sorted(np.random.choice(range(1, len(parent1) - 1), size=2, replace=False))
        child1 = np.concatenate((parent1[:point1], parent2[point1:point2], parent1[point2:]))
        child2 = np.concatenate((parent2[:point1], parent1[point1:point2], parent2[point2:]))
        return child1, child2

    def mutation(self, induvidual):
        for i in range(len(induvidual)):
            if np.random.rand() <= self.mutation_prob:
                induvidual[i] = 1 - induvidual[i]
        return induvidual
