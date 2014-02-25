CIPHER=-rc4
PASS='VerySecure'

PREFIX=out
SRC=src
TMP=tmp

all: prepare ${PREFIX}/final.ppm


${PREFIX}/final.ppm: ${PREFIX}/3a.ppm ${PREFIX}/3b.ppm ${TMP}/xor
	./${TMP}/xor ${TMP}/tux-head.enc.raw ${TMP}/tux-ass.enc.raw ${TMP}/tux.xor
	cat ${TMP}/tux-ass.raw.header ${TMP}/tux.xor > $@

${PREFIX}/3b.ppm: ${TMP}/tux-ass.raw
	openssl enc ${CIPHER} -nosalt -pass pass:${PASS} -in $< -out ${TMP}/tux-ass.enc.raw
	cat ${TMP}/tux-ass.raw.header ${TMP}/tux-ass.enc.raw > $@

${PREFIX}/3a.ppm: ${TMP}/tux-head.raw
	openssl enc ${CIPHER} -nosalt -pass pass:${PASS} -in $< -out ${TMP}/tux-head.enc.raw
	cat ${TMP}/tux-head.raw.header ${TMP}/tux-head.enc.raw > $@

${TMP}/tux-ass.raw: ${SRC}/tux.ppm ${TMP}/white_ppm
	${TMP}/white_ppm -b $< $@ $@.header
	cat $@.header $@ > ${PREFIX}/2b.ppm

${TMP}/tux-head.raw: ${SRC}/tux.ppm ${TMP}/white_ppm
	${TMP}/white_ppm -t $< $@ $@.header
	cat $@.header $@ > ${PREFIX}/2a.ppm

${TMP}/white_ppm: ${SRC}/white_ppm.c
	cc -g -o $@ $<

${TMP}/xor: ${SRC}/xor.c
	cc -g -o $@ $<

${TMP}:
	mkdir ${TMP}

${PREFIX}:
	mkdir ${PREFIX}
	cp ${SRC}/tux.ppm ${PREFIX}/1.ppm

prepare: ${TMP} ${PREFIX}


clean:
	rm -rf ${TMP}
	rm -rf ${PREFIX}
