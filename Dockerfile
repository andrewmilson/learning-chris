FROM ubuntu:latest
COPY bitmap.c fuaq.c
RUN gcc fuaq.c -o fuaq
CMD ["fuaq"]
