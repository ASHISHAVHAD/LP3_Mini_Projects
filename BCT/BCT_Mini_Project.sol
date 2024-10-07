// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Charity {
    address public owner;
    uint256 public totalDonations;

    struct Donation {
        address donor;
        uint256 amount;
        uint256 timestamp;
    }

    struct CharityProject {
        string name;
        address payable charityAddress;
        uint256 fundsAllocated;
    }

    mapping(address => uint256) public donations;
    mapping(address => Donation[]) public donorDonations;
    CharityProject[] public charityProjects;

    event DonationReceived(address indexed donor, uint256 amount);
    event FundsAllocated(address indexed charity, uint256 amount);

    modifier onlyOwner() {
        require(msg.sender == owner, "Only owner can call this function.");
        _;
    }

    constructor() {
        owner = msg.sender;
    }

    function donate() public payable {
        require(msg.value > 0, "Donation must be greater than zero.");
        
        donations[msg.sender] += msg.value;
        totalDonations += msg.value;

        donorDonations[msg.sender].push(Donation({
            donor: msg.sender,
            amount: msg.value,
            timestamp: block.timestamp
        }));

        emit DonationReceived(msg.sender, msg.value);
    }

    function addCharityProject(string memory _name, address payable _charityAddress) public onlyOwner {
        charityProjects.push(CharityProject({
            name: _name,
            charityAddress: _charityAddress,
            fundsAllocated: 0
        }));
    }

    function allocateFunds(uint256 _projectId, uint256 _amount) public onlyOwner {
        require(_projectId < charityProjects.length, "Invalid project ID.");
        require(_amount <= address(this).balance, "Insufficient funds.");

        CharityProject storage project = charityProjects[_projectId];
        project.charityAddress.transfer(_amount);
        project.fundsAllocated += _amount;

        emit FundsAllocated(project.charityAddress, _amount);
    }

    function getDonationHistory(address _donor) public view returns (Donation[] memory) {
        return donorDonations[_donor];
    }

    function getCharityProjects() public view returns (CharityProject[] memory) {
        return charityProjects;
    }
}