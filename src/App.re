[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo: string = "./logo.svg";

type route =
  | Games
  | Board;

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {route: Games},
  reducer,
  render: self =>
    switch (self.state.route) {
    | Games => <Games />
    | Board => <Board />
    },
};