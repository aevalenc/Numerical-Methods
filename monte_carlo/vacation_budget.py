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
    flight_cost_samples = rng_generator.uniform(flight_cost_min, flight_cost_max, number_of_samples)

    hotel_nightly_cost_min = 80
    hotel_nightly_cost_max = 200
    hotel_nightly_cost_samples = rng_generator.uniform(
        hotel_nightly_cost_min, hotel_nightly_cost_max, number_of_samples
    )

    total_cost_dist = flight_cost_samples + (hotel_nightly_cost_samples * 3)

    # using tuple unpacking for multiple Axes
    fig, (ax1, ax2) = plt.subplots(1, 2)
    ax1.set_title("Density Distribution")
    ax1.hist(total_cost_dist, density=True)
    ax2.set_title("Cumulative Distribution")
    ax2.hist(total_cost_dist, cumulative=True, density=True)
    plt.show()

    print(np.mean(total_cost_dist))


if __name__ == "__main__":
    print("Running Monte Carlo simulation for vacation budget planning")
    main()
