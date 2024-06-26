RM       = rm -rf
CLANG    = clang-14
LLVMLINK = llvm-link-14
LLI      = lli-14
ARMCC    = arm-linux-gnueabihf-gcc
QEMU     = qemu-arm

BUILD_DIR = "$(CURDIR)/build"
SRC_DIR   = "$(CURDIR)/src"
TEST_DIR  = "$(CURDIR)/test"

MAIN_EXE  = "$(BUILD_DIR)/main"

MAKEFLAGS = --no-print-directory

.PHONY: build clean veryclean rebuild compile run-llvm run-rpi

build:
	@cd $(SRC_DIR); \
	cmake -G Ninja -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release; \
	cd $(BUILD_DIR) && ninja; \
	cd $(CURDIR)

clean:
	@find $(TEST_DIR) -type f \( \
		-name "*.ll" -o -name "*.xml" -o -name "*.output" \
		-o -name "*.src" -o -name "*.ast" -o -name "*.irp" \
		-o -name "*.stm" -o -name "*.ins" -o -name "*.ssa" \
		-o -name "*.cfg" -o -name "*.rpi" -o -name "*.arm" \
		-o -name "*.s" \
		\) -exec $(RM) {} \;

veryclean: clean
	@$(RM) $(BUILD_DIR)

rebuild: veryclean build

compile: clean
	@cd $(TEST_DIR)/tmp; \
	for file in $$(ls .); do \
		if [ "$${file##*.}" = "fmj" ]; then \
			echo "Compiling [$${file%%.*}]"; \
			$(MAIN_EXE) "$${file%%.*}" < "$${file%%.*}".fmj; \
		fi \
	done; \
	cd $(CURDIR)

run-llvm: rebuild
	@cd $(TEST_DIR); \
	for file in $$(ls .); do \
		if [ "$${file##*.}" = "fmj" ]; then \
			echo "Run on llvm for [$${file%%.*}]"; \
			$(MAIN_EXE) "$${file%%.*}" < "$${file%%.*}".fmj; \
			$(LLVMLINK) --opaque-pointers "$${file%%.*}".6.ssa $(BUILD_DIR)/vendor/libsysy/libsysy64.ll -S -o "$${file%%.*}".ll && \
			$(LLI) -opaque-pointers "$${file%%.*}".ll > "$${file%%.*}".output && \
			echo $$?; \
		fi \
	done; \
	cd $(CURDIR)

run-rpi: rebuild
	@cd $(TEST_DIR); \
	for file in $$(ls .); do \
		if [ "$${file##*.}" = "fmj" ]; then \
			echo "Run on arm for [$${file%%.*}]"; \
			$(MAIN_EXE) "$${file%%.*}" < "$${file%%.*}".fmj; \
			$(ARMCC) -mcpu=cortex-a72 "$${file%%.*}".8.s $(BUILD_DIR)/vendor/libsysy/libsysy32.s --static -o "$${file%%.*}".s && \
			$(QEMU) -B 0x1000 "$${file%%.*}".s > "$${file%%.*}".output && \
			echo $$?; \
		fi \
	done; \
	cd $(CURDIR)
