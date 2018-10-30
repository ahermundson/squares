type user = {_id: string};

type square = {
  .
  isTaken: bool,
  x: int,
  y: int,
  takenByUserID: option(user),
};