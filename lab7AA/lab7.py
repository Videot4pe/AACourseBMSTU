import random
import math

class Ant:
    def __init__(self, tourSize):
        self.trailSize = tourSize
        self.trail = [0 for _ in range(tourSize)]
        self.visitedCities = [False for _ in range(tourSize)]

    def visitCity(self, currentIndex, city):
        self.trail[currentIndex + 1] = city
        self.visitedCities[city] = True

    def isVisited(self, i):
        return self.visitedCities[i]

    def trailLength(self, graph):
        length = graph[self.trail[self.trailSize - 1]][self.trail[0]]
        for i in range(self.trailSize - 1):
            length += graph[self.trail[i]][self.trail[i + 1]]
        return length

    def clear(self):
        for i in range(self.trailSize):
            self.visitedCities[i] = False

class ACO:
    def __init__(self, alpha, beta, evaporation,
             Q, graph, ants):
        self.c = 1.0
        self.alpha = alpha
        self.beta = beta
        self.evaporation = evaporation
        self.Q = Q
        self.antFactor = 1
        self.randomFactor = 0.01
        self.maxIterations = 1000
        self.graph = graph
        self.numberOfCities = len(graph)
        self.numberOfAnts = int(float(self.numberOfCities) * self.antFactor)
        self.currentIndex = 0
        self.bestTourOrder = []
        self.bestTourLength = 0.0
        self.ants = ants
        self.trails = [[0.001 for i in range(self.numberOfCities)] for i in range(self.numberOfCities)]
        self.probabilities = [0.0 for i in range(self.numberOfCities)]

    def solveACO(self):
        self.setupAnts()
        self.clearTrails()
        for i in range(self.maxIterations):
            self.currentIndex = 0
            for ant in ants:
                ant.clear()
                ant.visitCity(-1, ant.trail[0])
            self.moveAnts()
            self.updateTrails()
            self.updateBest()

        return [] + self.bestTourOrder, self.bestTourLength - float(self.numberOfCities)

    def setupAnts(self):
        for _ in range(self.numberOfAnts):
            for i in range(len(self.ants)):
                self.ants[i].clear()
                self.ants[i].visitCity(-1, random.randint(0, self.numberOfCities - 1))
        self.currentIndex = 0

    def moveAnts(self):
        for _ in range(self.currentIndex, self.numberOfCities - 1):
            for i in range(len(ants)):
                self.ants[i].visitCity(self.currentIndex, self.selectNextCity(self.ants[i]))
            self.currentIndex += 1

    def selectNextCity(self, ant):
        self.calculateProbabilities(ant)
        r = random.random() * sum(self.probabilities)
        total = 0.0
        for i in range(self.numberOfCities):
            total += self.probabilities[i]
            if total >= r:
                return i
        print(self.probabilities)
        print("No cities left\n")

    def calculateProbabilities(self, ant):
        i = ant.trail[self.currentIndex]
        sum = 0
        for l in range(self.numberOfCities):
            sum += math.pow(self.trails[i][l], self.alpha) / math.pow(self.graph[i][l], self.beta)
        for j in range(self.numberOfCities):
            if ant.isVisited(j):
                self.probabilities[j] = 0
            else:
                self.probabilities[j] = math.pow(self.trails[i][j], alpha) / math.pow(self.graph[i][j], self.beta) / sum

    def updateTrails(self):
        for i in range(self.numberOfCities):
            for j in range(self.numberOfCities):
                self.trails[i][j] *= 1 - self.evaporation

        for i in range(len(self.ants)):
            contribution = self.Q / self.ants[i].trailLength(self.graph)
            for j in range(self.numberOfCities - 1):
                self.trails[self.ants[i].trail[j]][self.ants[i].trail[j + 1]] += contribution
            self.trails[self.ants[i].trail[self.numberOfCities - 1]][self.ants[i].trail[0]] += contribution

    def updateBest(self):
        if not len(self.bestTourOrder):
            for i in range(self.numberOfCities):
                self.bestTourOrder.append(self.ants[0].trail[i])
            self.bestTourLength = self.ants[0].trailLength(self.graph)
        for i in range(len(self.ants)):
            if self.ants[i].trailLength(self.graph) < self.bestTourLength:
                self.bestTourLength = self.ants[i].trailLength(self.graph)
                for j in range(self.numberOfCities):
                    self.bestTourOrder[j] = self.ants[i].trail[j]

    def clearTrails(self):
        for i in range(self.numberOfCities):
            for j in range(self.numberOfCities):
                self.trails[i][j] = self.c

if __name__ == "__main__":
    citiesCount = 10
    antFactor = 1
    graph = [[random.randint(1, 100) for _ in range(citiesCount)] for _ in range(citiesCount)]
    print(graph)
    ants = []
    for i in range(int(float(citiesCount) * antFactor)):
        ant = Ant(citiesCount)
        ants.append(ant)
    alpha = float(input("input alpha: "))
    beta = int(input("input beta: "))
    evaporation = float(input("input evaporation: "))
    Q = float(input("input Q: "))
    algorithm = ACO(alpha, beta, evaporation,
        Q, graph, ants)
    result, minlength = algorithm.solveACO()
    print(result, minlength)
