FROM alpine:3.18 AS builder
RUN apk add --no-cache gcc musl-dev make
WORKDIR /app
COPY . .
RUN make

FROM alpine:3.18
WORKDIR /app
COPY --from=builder /app/persona_turk .
ENTRYPOINT ["./persona_turk"]
