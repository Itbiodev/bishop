import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("benchmark_results.csv")

plt.figure(figsize=(10, 6))
sns.set_style("whitegrid")

for program in df["program"].unique():
    program_data = df[df["program"] == program]
    plt.errorbar(
        program_data["input_size"],
        program_data["mean"],
        yerr=program_data["stddev"],
        label=program,
        marker="o",
    )

plt.xscale("log")
plt.yscale("log")
plt.xlabel("Input Size")
plt.ylabel("Execution Time (seconds)")
plt.title("Performance Comparison")
plt.legend()

plt.savefig("benchmark_results.png")
plt.close()
