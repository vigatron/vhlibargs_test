import os
import subprocess


EXE_OK = 0
EXE_NO = 1

CURDIR  = os.path.dirname(os.path.abspath(__file__))
APPDIR  = os.path.dirname(CURDIR) + "/build"
APPFILE = "./vhlibargs_test"

ARR_PATTERN_TESTS = [

    [EXE_OK, [], "Dry run / no params"],
    [EXE_OK, ["param1","param2","param3"], "Simple params test"],
    [EXE_OK, ["-add", "-va", "3", "-vb", "2"], "Test add"],

    [EXE_NO, ["-add", "-va"], "E: Missed parameter"],
    [EXE_NO, ["-att"], "E: Unknown parameter"],
    [EXE_NO, ["-add", "-sub"], "E: Conflicting commands"],

]


def runtest(item):
    expected_result = item[0]
    paramsarr = item[1]
    description = item[2]

    callarr = [APPFILE]
    for param in paramsarr:
        callarr.append(param)

    exec_result = subprocess.run(
        callarr,
        cwd=APPDIR,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL )
    if exec_result.returncode != expected_result:
        return False

    return True


if __name__ == "__main__":
    print("Testing vhlibargs_test int " + APPDIR )
    for item in ARR_PATTERN_TESTS:
        txtparams = " ".join(item[1])
        txtcall = " | " + f"{txtparams:<24}" + " | " + item[2]

        r = runtest(item)
        txtstatus = "FAILED" if not r else "OK"
        print(f"{txtstatus:<8} | {item[0]} " + txtcall)

        # Exit on failed test
        if not r:
            exit(1) 


    print("All tests passed")
    exit(0)
