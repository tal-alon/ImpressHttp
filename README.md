# ImpressHttp
An http micro framework written in c++ (a word play on the Express.js framework)

## Problems
- When sending 11 async requests with python's aiohttp the operation never completes.  
The server blocks the 11th request (since it supports only 10 connections at a time).

## Open Questions
- Determine a headers size limit, maybe 1kb?

## Notes
#### Path / Url / Query Parameters
- The server will treat a query without an '=' as empty value.
  e.g. `?key` will be treated as `?key=`
- The path parser currently does not support a fragment identifier (e.g. `#fragment`).  
  Sending a path with a fragment identifier will result in undefined behavior.