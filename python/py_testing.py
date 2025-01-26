import pytest

# Fixture to provide setup data
@pytest.fixture
def setup_data():
    return {"name": "pytest", "version": 7}

# Test case using the fixture
def test_name(setup_data):
    assert setup_data["name"] == "pytest"

def test_version(setup_data):
    assert setup_data["version"] == 7
    assert setup_data["name"] == "pytest"

def test_subtraction():
    assert 5 - 3 == 2