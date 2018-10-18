[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo: string = "./logo.svg";

open SharedTypes;

type row = list(square);
type board = list(row);
type user = {
  name: string,
  id: int,
};

let makeRow = (i, id) =>
  Belt.List.makeBy(10, (j: int) =>
    ({isTaken: false, id: id + j, x: i, y: j, takenByUserID: None}: square)
  );

let board: board = [
  makeRow(0, 0),
  makeRow(1, 10),
  makeRow(2, 20),
  makeRow(3, 30),
  makeRow(4, 40),
  makeRow(5, 50),
  makeRow(6, 60),
  makeRow(7, 70),
  makeRow(8, 80),
  makeRow(9, 90),
];

type state = {
  board,
  currentUserID: option(int),
};

type action =
  | ClickSquare(square)
  | AddUser;

let component = ReasonReact.reducerComponent("App");

let str = ReasonReact.string;

let updateBoard =
    (board: board, clickedSquare: square, currentUserID: option(int)) =>
  board
  |> List.map(row =>
       row
       |> List.map((square: square) =>
            square.id == clickedSquare.id ?
              {...square, isTaken: true, takenByUserID: currentUserID} :
              square
          )
     );

let make = _children => {
  ...component,
  initialState: () => ({board, currentUserID: None}: state),
  reducer: (action: action, state: state) =>
    switch (action) {
    | ClickSquare(clickedSquare) =>
      ReasonReact.Update({
        ...state,
        board: updateBoard(state.board, clickedSquare, state.currentUserID),
      })
    | AddUser => ReasonReact.Update({...state, currentUserID: Some(1)})
    },
  render: ({state, send}) =>
    switch (state.currentUserID) {
    | None =>
      <button onClick=(_evt => send(AddUser))> {str("Test")} </button>
    | Some(_userID) =>
      <div className="App">
        <h1> {str("Squares")} </h1>
        {
          state.board
          |> List.mapi((id: int, row) =>
               <BoardRow
                 key={string_of_int(id)}
                 row
                 click=(x => send(ClickSquare(x)))
               />
             )
          |> Array.of_list
          |> ReasonReact.array
        }
      </div>
    },
};