RM = rm -rf

BUILD_DIR = "$(CURDIR)/build"
SRC_DIR   = "$(CURDIR)/src"
TEST_DIR  = "$(CURDIR)/test"

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

compile:
	@cd $(TEST_DIR); \
	for file in $$(ls .); do \
		if [ "$${file##*.}" = "fmj" ]; then \
			echo "Compiling [$${file%%.*}]"; \
		fi \
	done; \
	cd $(CURDIR)

run-llvm:
	@cd $(TEST_DIR); \
	for file in $$(ls .); do \
		if [ "$${file##*.}" = "fmj" ]; then \
			echo "Run on llvm for [$${file%%.*}]"; \
		fi \
	done; \
	cd $(CURDIR)

run-rpi:
	@cd $(TEST_DIR); \
	for file in $$(ls .); do \
		if [ "$${file##*.}" = "fmj" ]; then \
			echo "Run on arm for [$${file%%.*}]"; \
		fi \
	done; \
	cd $(CURDIR)
