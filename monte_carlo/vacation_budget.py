"""
Monte Carlo simulation for vacation budget planning.
"""

import random

import matplotlib.pyplot as plt
import numpy as np


def main():

    rng_generator = np.random.default_rng(seed=10)

    number_of_samples = 1000

    flight_cost_min = 500
    flight_cost_max = 1000
    # flight_cost_dist = np.random.uniform(flight_cost_min, flight_cost_max, number_of_samples)
    # flight_cost_samples = rng_generator.uniform(flight_cost_min, flight_cost_max, number_of_samples, endpoint=True)
    flight_cost_samples = rng_generator.uniform(flight_cost_min, flight_cost_max, number_of_samples)
    # print(f"Flight cost samples: {flight_cost_samples}")

    hotel_nightly_cost_min = 80
    hotel_nightly_cost_max = 200
    hotel_nightly_cost_samples = rng_generator.uniform(
        hotel_nightly_cost_min, hotel_nightly_cost_max, number_of_samples
    )

    total_cost_dist = flight_cost_samples + (hotel_nightly_cost_samples * 3)

    # plt.figure()
    # count, bins, ignored = plt.hist(flight_cost_dist, 10, density=True)
    # plt.plot(bins, np.ones_like(bins), linewidth=2, color="r")

    plt.figure()
    counts, bins = np.histogram(flight_cost_samples, bins="auto")
    print(f"Bins: {bins}")
    print(f"Counts: {counts}")
    # plt.plot(bins[:-1], counts)
    plt.hist(flight_cost_samples, edgecolor="black", align="mid")
    plt.title("Flight Cost Distribution")

    plt.figure()
    # plt.hist(bins[:-1], bins, weights=counts)
    plt.title("Flight Cost Distribution Density")
    plt.hist(flight_cost_samples, density=True)

    plt.figure()
    plt.title("Flight Cost Distribution Cummulative")
    plt.hist(total_cost_dist, number_of_samples, cumulative=True, density=True)
    plt.show()

    print(np.mean(total_cost_dist))


if __name__ == "__main__":
    print("Running Monte Carlo simulation for vacation budget planning")
    main()
