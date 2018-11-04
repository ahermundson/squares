[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo: string = "./logo.svg";

type route =
  | Games
  | Board;

type state = {
  route,
  selectedGame: option(string),
};

type action =
  | SelectGame(string);

let reducer = (action, _state) =>
  switch (action) {
  | SelectGame((id: string)) =>
    ReasonReact.Update({selectedGame: Some(id), route: Board})
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {route: Games, selectedGame: None},
  reducer,
  render: self =>
    switch (self.state.route) {
    | Games => <Games selectGame=(id => self.send(SelectGame(id))) />
    | Board =>
      switch (self.state.selectedGame) {
      | Some(selectedGame) => <Board selectedGame />
      | None => <h1> {ReasonReact.string("Error")} </h1>
      }
    },
};