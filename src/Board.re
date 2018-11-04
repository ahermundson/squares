[%bs.raw {|require('./App.css')|}];

open SharedTypes;
module GetGameSquares = [%graphql
  {|
    query getThoseGameSquares($id: ID!) {
        getGameSquares(id: $id) {
            _id
            x
            y
            isTaken
        }
    }
  |}
];

module GetGameSquareQuery = ReasonApollo.CreateQuery(GetGameSquares);

type row = Js.Array.t(square);
type board = Js.Array.t(row);
type state = {currentUserID: option(int)};
type action =
  | ClickSquare(square)
  | AddUser;

let component = ReasonReact.reducerComponent("App");

let str = ReasonReact.string;

let createBoardRow = (squares, x) =>
  squares |> Js.Array.filter(square => square##x == x);

let parseSquares = squares =>
  switch (squares) {
  | None => [||]
  | Some(squares) => [|
      createBoardRow(squares, 0),
      createBoardRow(squares, 1),
      createBoardRow(squares, 2),
      createBoardRow(squares, 3),
      createBoardRow(squares, 4),
      createBoardRow(squares, 5),
      createBoardRow(squares, 6),
      createBoardRow(squares, 7),
      createBoardRow(squares, 8),
      createBoardRow(squares, 9),
    |]
  };

let clicker = test => Js.log(test);
let make = (~selectedGame, _children) => {
  ...component,
  initialState: () => ({currentUserID: None}: state),
  reducer: (action: action, _state: state) =>
    switch (action) {
    | ClickSquare(_clickedSquare) =>
      ReasonReact.Update({currentUserID: Some(1)})
    | AddUser => ReasonReact.Update({currentUserID: Some(1)})
    },
  render: ({state, send}) =>
    switch (state.currentUserID) {
    | None =>
      <button onClick=(_evt => send(AddUser))> {str("Test")} </button>
    | Some(_userID) =>
      let gameQuery = GetGameSquares.make(~id=selectedGame, ());
      <div className="App">
        <h1> {str("Squares")} </h1>
        <GetGameSquareQuery variables=gameQuery##variables>
          ...(
               ({result}) =>
                 switch (result) {
                 | Loading => <h1> {str("Loading")} </h1>
                 | Error(error) =>
                   Js.log(error);
                   <h1> {str("Error")} </h1>;
                 | Data(response) =>
                   let gameSquares = response##getGameSquares;
                   let parsedRows = parseSquares(gameSquares);
                   parsedRows
                   |> Js.Array.mapi((row, i) =>
                        <BoardRow key={string_of_int(i)} row click=clicker />
                      )
                   |> ReasonReact.array;
                 }
             )
        </GetGameSquareQuery>
      </div>;
    },
};