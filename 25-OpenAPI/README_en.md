# 05 · OpenAPI and Reproducible Data Ingestion

 We build the closed-loop twin pipeline's **very first piece, ① observation ingestion**. We
start a **local mock weather API** inside the notebook that imitates the response structure of
the KMA public-data OpenAPI, and learn **real HTTP ingestion** with `requests` on top of it —
deterministic and green offline, while the code transfers unchanged to the real KMA endpoint.
This week's deliverable is a **reproducible observation ingestion script**.  

## What it covers

- **Anatomy of a request**: an OpenAPI = base URL + query parameters + authentication key,
  with a table of HTTP status codes. How `requests` encodes parameters into a URL.
- **Status code vs resultCode**: the public data portal returns HTTP 200 even on an
  authentication failure, with `resultCode='30'` in the body — we hit this for real and learn
  to check both.
- **Parsing**: the JSON, XML and CSV serialisations parsed separately and verified to yield
  identical records (to within $10^{-9}$).
- **Pagination**: `pageNo`/`numOfRows`/`totalCount` used to collect all 576 rows with no
  duplicates and no gaps (⌈576/100⌉=6 pages).
- **Reproducibility**: cache + SHA-256 checksum + manifest proving "same request → same data".
- **Network/credential isolation**: the real KMA call (ultra-short-term nowcast via data.go.kr) lives only inside a `KMA_API_KEY`
  guard.
 

## Where this sits in the closed-loop twin pipeline

It completes the **① observation ingestion** stretch — building the reproducible entrance
that fetches, in the first place, the observations Week 4's space-time alignment (②) consumes,
and building an **M0 baseline** from them. M1 (Week 8, ML), M2 (Week 11, physics) and M3
(Week 13, hybrid) must all beat this M0.

 