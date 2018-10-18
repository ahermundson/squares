external register_service_worker: unit => unit = "default";

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let httpLink =
  ApolloLinks.createHttpLink(~uri="http://localhost:4000/graphql", ());

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=instance> <App /> </ReasonApollo.Provider>,
  "root",
);