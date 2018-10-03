[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <h1>(ReasonReact.string("This is my first Reason React app."))</h1>
    </div>,
};
