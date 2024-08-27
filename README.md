# ImpressHttp
An http micro framework written in c++ (a word play on the Express.js framework)

## Open Questions
- Determine a headers size limit, maybe 1kb? 

## Notes
#### Query Parameters
- The server will treat a query without an '=' as empty value.
  e.g. `?key` will be treated as `?key=`