FROM ubuntu:22.04 AS build-env

RUN apt-get update -y
RUN apt-get install -y build-essential libcriterion-dev

WORKDIR /app

COPY . .

RUN make

CMD ["./bin/test"]
