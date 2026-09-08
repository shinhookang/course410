# 01 · Big Data Systems and Digital Twins — An Overview

**Notebook:** [`week01_overview_en.ipynb`](./week01_overview_en.ipynb)
(English edition of [`week01_overview.ipynb`](./week01_overview.ipynb) — same code,
same numbers, same figures.)

We complete a miniature of the whole semester in about 40 lines of simulation, so
that the full structure of the **closed-loop digital twin** this course builds is
experienced in the very first week.

## What it covers

- **A digital twin is a closed loop**: observations update the state, and the
  updated state forecasts the future. Real systems: DestinE (ECMWF), NOAA EODT.
- The **five stages of the end-of-semester pipeline** (ingest observations → align
  in space-time → forecast state → update with observations → dashboard) and how
  they map to weeks and tools.
- Marching a **synthetic urban temperature field** with heat diffusion (verifying
  the stability condition α·Δt/Δx² ≤ 1/4) — the seed of the running example of
  Weeks 10–13.
- Implementing **persistence (M0), open-loop and closed-loop** forecasts on the
  same problem and comparing them by RMSE. One line of nudging cuts the error by
  17% relative to open-loop.
- The **Kaggle competition**: problem definition, RMSE, milestones (M0→M4), and
  the score conversion formula.
- Estimating the **data volume** of real observational datasets → why distributed
  and parallel processing is needed.

## Key message

Persistence is a remarkably strong baseline at short lead times, so the first
week's twin does not beat it yet. **Finally overtaking a strong persistence
baseline with physics + observations** is the semester-long journey from M0 to M3.

## Kaggle

This week **introduces** the competition — the problem structure and the
evaluation (RMSE, 5 submissions per day). The competition opens in Week 3; the
first milestone M0 is due in Week 5.

## Build

```bash
cd ../_build && /Users/pepc/Teaching/410/.venv/bin/python3 build_week01_en.py
```
