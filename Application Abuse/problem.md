# 🔍 Application Abuse

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 IEEE Xplore

Warm greetings to all IEEExtreme Participants from the Xplore API Team!

As part of the IEEExtreme Competition, you will face a programming challenge where you'll need to analyze web application logs to identify potential instances of application misuse.

For a full dynamic database search IEEE Xplore API is available for your IEEE research needs. Xplore API provides metadata on 4.9mn academic works and is now delivering full-text content on 50k 'Open Access' articles. Xplore API will make your research needs fast and easy. The Xplore API Portal supports PHP, Python and Java as well as providing output in JSON and XML formats. Many API use cases are listed within the API Portal.

Xplore API registration is free. To learn more about IEEE Xplore API please visit [developer.ieee.org](https://developer.ieee.org/) and register for an API key TODAY!

---

## 🎯 Challenge

Users log into the IEEE document repository application to search for articles, download PDFs, view abstracts, and perform various other tasks. To access the application, users must agree to the acceptable usage terms. Your task is to **identify users who are violating these terms**.

---

## 📥 Standard Input

The input consists of three parts: a web log descriptor, rules of abuse, and web log entries. The first row outlines the rules of abuse, which detail five potential ways individuals can misuse the system:

1. Using **X** or more different user agents in a single day, indicated by `agent=X`
2. Using **X** or more different IP addresses in a single day, indicated by `ip=X`
3. Downloading PDFs at least **X** times, indicated by `pdf=X`
4. Initiating **X** or more sessions, indicated by `session=X`
5. Engaging in **X** or more crawling activities in a single day, indicated by `crawl=X`

The settings can be listed in any order. For example:

1. `agent=3, ip=4, pdf=10, session=20, crawl=10`
2. `session=20, pdf=100`

Not every situation requires a comprehensive set of rules. For example, you may only need to check for the existence of **session** and **pdf** abuse, without the need for additional rules.

---

### 📊 Abuse Detection Rules

**Sequential PDF Downloads:**
To determine if an individual is using a robot to download PDFs sequentially, examine the order of the PDF downloads. For example, if the user downloads the PDFs in the following order:
```
1.pdf, 2.pdf, 3.pdf, ..., 10.pdf
```
This indicates they are likely using a robot. There can be other page requests in between PDF requests. For example:
```
1.pdf, /search/criteria, 2.pdf, /search/results, ..., 10.pdf
```
This is **still considered abuse**.

If the user downloads more than the specified number of PDFs sequentially (set by the parameter `crawl=X`), report this in the output. The downloads must be in sequential order by date and time to be considered part of the same robot-driven download session.

For instance, if the user downloads the PDFs in the order `1.pdf, 4.pdf, 2.pdf, 9.pdf`, this is not considered sequential and would not reach the limit of `crawl=4` downloads sequentially, even though `<=4` PDFs were downloaded.

**Session Counting:**
Keep track of the ids and check if the number of sessions for each id is equal to or greater than a specified setting. For instance, if a certain individual has 10 sessions and the setting is set to `session=5`, then in the output, print `[id] session=10`.

**Daily Timeframe:**
When considering the rules, remember that the settings are based on a **daily** timeframe. So, if the log entries cover multiple days, you may not identify any abuse when looking at individual days, even though there might be abuse when considering the entire set of log entries.

---

### 📄 Log File Descriptor

The second row contains the log file descriptor. The log file contains the following fields:

1. **Host** – Domain name. For example, `documents.ieee.org`
2. **Client IP** – IP address of the client that is making a request to the server
3. **Id** – Unique string identifying the individual
4. **Date** – Date of the request. The format will be `[dd/Mmm/YYYY:HH24:mm:ss]`. Example: `[07/Oct/2025:14:26:41]`
5. **Request** – The URL requested. For example, `"GET /article/abstract?id=XYZ HTTP/1.1"`
6. **HTTP Status** – Standard list of HTTP Status Codes. See [Wikipedia - List of HTTP status codes](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)
7. **User Agent** – A string of text that identifies the client software originating a request
8. **Session Cookie** – A string used to track a user's interactions during a single session

All fields will be present. However, the order is not always the same. Examples:

1. `Host, Client IP, Id, Date, Request, HTTP Status, User Agent, Session Cookie`
2. `Host, Client IP, Date, Request, HTTP Status, User Agent, Session Cookie, Id`

The remaining rows will be the log entries. If a field has no value, it will be set to a dash `"-"`.

**Example log entries:**
```
documents.ieee.org 131.155.123.139 XYZ [07/Feb/2024-12:26:41] "GET /document/abstract?id=123 HTTP/1.1" 200 "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36" "session-id-123"

documents.ieee.org 131.155.136.122 - [18/Mar/2025:18:20:55] "GET /document/123.pdf HTTP/1.1" 200 "Mozilla/5.0 (Windows Mobile 10; Android 10.0; Microsoft; Lumia 950XL) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Mobile Safari/537.36 Edge/40.15254.603" "cookie1"
```

The Date will always be enclosed by square brackets and the User Agent, Request and Session Cookie will always be enclosed by double quotes.

Usually, any HTTP Status code other than **200** should be ignored and not counted towards a violation.

---

## 📤 Standard Output

For each violation write out the id followed by the abuse type and the value. Sort by id with a secondary sort of abuse type.

---

## 🔒 Constraints and Notes

- Number of records ≤ 10,000
- A request for a PDF download will always take the form `"GET /document/{XXX}.pdf HTTP/1.1"` where `{XXX}` is a string containing numbers only
- **XYZ** may be one of the ids in the log file
- If there are no ids that have abuse simple print `N/A` in the output
- There will not be duplicate abuse of the same type for the same id over multiple days. For instance, if the pdf abuse is set as 10 and there are two days contained in the file, you will never have the case `XYZ pdf=11` for 01/01/2025 and `XYZ pdf=12` for 01/02/2025

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **log analysis and pattern detection** problem:

1. **Parse Input**
   - Read abuse rules (agent, ip, pdf, session, crawl thresholds)
   - Read log descriptor to understand field ordering
   - Parse each log entry according to descriptor

2. **Track User Activities**
   - For each user ID, maintain:
     - Set of unique user agents per day
     - Set of unique IPs per day
     - Count of PDF downloads per day
     - Set of unique session cookies
     - Sequence of PDF downloads for crawl detection

3. **Detect Violations**
   - **Agent abuse:** Count unique user agents per user per day
   - **IP abuse:** Count unique IPs per user per day
   - **PDF abuse:** Count total PDF downloads per user per day
   - **Session abuse:** Count unique sessions per user
   - **Crawl abuse:** Detect sequential PDF downloads (1.pdf, 2.pdf, 3.pdf, ...)

4. **Sequential Crawl Detection**
   - Track PDF download order for each user
   - Check if PDFs are downloaded in numerical order
   - Allow intervening non-PDF requests
   - Count longest sequential streak

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N log N) |
| **Space** | O(N) |

**Where:**
- N = number of log entries (≤ 10,000)

---

## 🔑 Key Insights

- ✨ **Parse log format dynamically** based on descriptor
- ✨ Track activities **per user per day** for agent, ip, pdf rules
- ✨ **Session counting** is across all days (not daily)
- ✨ **Crawl detection** requires tracking PDF download order
- ✨ Only count HTTP status **200** responses
- ✨ Handle missing fields (represented as `"-"`)
- ✨ **Sort output** by ID first, then by abuse type
- ✨ Sequential PDFs: 1.pdf → 2.pdf → 3.pdf (numeric order)

---

## 📚 Related Topics

- Log Analysis
- Pattern Detection
- String Parsing
- Data Structures (Hash Maps, Sets)
- Sequence Detection
- Web Application Security
- Bot Detection

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>