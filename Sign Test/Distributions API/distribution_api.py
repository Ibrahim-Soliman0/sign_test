from fastapi import FastAPI
from scipy.stats import binom, norm

app = FastAPI()

@app.get("/api/normal")
def get_normal_distribution(alpha):
    alpha = float(alpha)
    z_value = norm.ppf(1 - alpha)
    z_value = round(z_value, 2)
    print(z_value)
    return {"z_value" : z_value}

@app.get("/api/binomial")
def get_binomial_distribution(n, alpha, p=0.5):
    n = int(n)
    alpha = float(alpha)
    k_dash = stats.binom.ppf(alpha, n, p)  
    k = stats.binom.ppf(1-alpha, n, p)
        
    return {'k_dash': int(k_dash-1), 'k': int(k+1)}